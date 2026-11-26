---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 06:07:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 72-76 cores)</summary>

```
1795690873 76
1795690878 76
1795690883 76
1795690888 76
1795690893 76
1795690898 76
1795690903 76
1795690908 76
1795690913 76
1795690918 76
1795690923 74
1795690928 74
1795690933 72
1795690938 72
1795690943 72
1795690948 72
1795690953 72
1795690958 72
1795690963 72
1795690968 72
```
</details>

---

