---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-21 10:08:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 43-44 cores)</summary>

```
1787321002 44
1787321007 44
1787321012 44
1787321017 44
1787321022 43
1787321027 43
1787321032 43
1787321037 43
1787321042 43
1787321047 43
1787321052 44
1787321057 44
1787321062 44
1787321067 44
1787321072 44
1787321077 44
1787321082 44
1787321087 44
1787321092 44
1787321097 44
```
</details>

---

