---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 08:20:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 261 |
| Sample Rate | 4.35/sec |
| Health Score | 272% |
| Threads | 14 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (2 unique values: 21-33 cores)</summary>

```
1795698919 21
1795698924 21
1795698929 21
1795698934 21
1795698939 21
1795698944 33
1795698949 33
1795698954 33
1795698959 33
1795698964 33
1795698969 33
1795698974 33
1795698979 33
1795698984 33
1795698989 33
1795698994 33
1795698999 33
1795699004 33
1795699009 33
1795699014 33
```
</details>

---

