---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 04:47:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1789979900 44
1789979905 49
1789979910 49
1789979915 49
1789979920 49
1789979925 49
1789979930 49
1789979935 44
1789979940 44
1789979945 44
1789979950 44
1789979955 44
1789979960 44
1789979965 44
1789979970 44
1789979975 44
1789979980 44
1789979985 44
1789979990 49
1789979995 49
```
</details>

---

