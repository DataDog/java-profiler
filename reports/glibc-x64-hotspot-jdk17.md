---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-27 09:51:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 23.43/sec |
| Health Score | 1464% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (5 unique values: 67-82 cores)</summary>

```
1769525012 76
1769525017 76
1769525022 76
1769525027 76
1769525032 76
1769525037 76
1769525042 76
1769525047 67
1769525052 67
1769525057 67
1769525062 67
1769525067 72
1769525072 72
1769525077 72
1769525082 72
1769525087 72
1769525092 72
1769525097 72
1769525102 72
1769525107 72
```
</details>

---

