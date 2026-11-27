---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-27 08:37:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 76-85 cores)</summary>

```
1795786350 76
1795786355 76
1795786360 76
1795786365 78
1795786370 78
1795786375 76
1795786380 76
1795786385 76
1795786390 76
1795786395 76
1795786400 76
1795786405 76
1795786410 76
1795786415 76
1795786420 76
1795786425 76
1795786430 76
1795786435 76
1795786440 76
1795786445 76
```
</details>

---

