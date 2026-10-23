---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 05:55:54 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1048 |
| Sample Rate | 17.47/sec |
| Health Score | 1092% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 27-35 cores)</summary>

```
1792749034 35
1792749039 35
1792749044 35
1792749049 35
1792749054 35
1792749059 35
1792749064 35
1792749069 35
1792749074 35
1792749079 35
1792749084 35
1792749089 35
1792749094 35
1792749099 35
1792749104 35
1792749109 35
1792749114 35
1792749119 35
1792749124 35
1792749129 35
```
</details>

---

