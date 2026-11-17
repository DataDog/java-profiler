---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 07:23:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 18-38 cores)</summary>

```
1794917962 18
1794917967 18
1794917972 38
1794917977 38
1794917982 38
1794917988 38
1794917993 38
1794917998 38
1794918003 38
1794918008 38
1794918013 38
1794918018 38
1794918023 38
1794918028 38
1794918033 38
1794918038 38
1794918043 38
1794918048 38
1794918053 38
1794918058 38
```
</details>

---

