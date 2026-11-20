---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 12:39:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 14 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795196086 45
1795196091 45
1795196096 45
1795196101 45
1795196106 45
1795196111 45
1795196116 45
1795196121 45
1795196126 45
1795196132 45
1795196137 45
1795196142 50
1795196147 50
1795196152 50
1795196157 50
1795196162 50
1795196167 50
1795196172 50
1795196177 50
1795196182 50
```
</details>

---

