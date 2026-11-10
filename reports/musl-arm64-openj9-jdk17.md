---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-11-10 10:42:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 25-25 cores)</summary>

```
1794324996 25
1794325001 25
1794325006 25
1794325011 25
1794325016 25
1794325021 25
1794325026 25
1794325031 25
1794325036 25
1794325041 25
1794325046 25
1794325051 25
1794325056 25
1794325061 25
1794325066 25
1794325071 25
1794325076 25
1794325081 25
1794325086 25
1794325091 25
```
</details>

---

