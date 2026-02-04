---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ❌ FAIL

**Date:** 2026-02-04 07:50:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | N/A |
| Sample Rate | N/A/sec |
| Health Score | N/A% |
| Threads | N/A |
| Allocations | N/A |

#### Scenario 2: Tracer+Profiler ⚠️
| Metric | Value |
|--------|-------|
| Status | N/A |
| CPU Samples | N/A |
| Sample Rate | N/A/sec |
| Health Score | N/A% |
| Threads | N/A |
| Allocations | N/A |

<details>
<summary>CPU Timeline (6 unique values: 59-87 cores)</summary>

```
1770208913 59
1770208918 59
1770208923 59
1770208928 59
1770208933 59
1770208938 59
1770208943 59
1770208948 59
1770208953 59
1770208958 59
1770208963 64
1770208968 64
1770208973 64
1770208978 64
1770208983 69
1770208988 69
1770208993 69
1770208998 77
1770209003 77
1770209008 82
```
</details>

---

