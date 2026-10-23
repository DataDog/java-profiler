---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 08:55:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 10 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 9 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 51-55 cores)</summary>

```
1792759875 51
1792759880 51
1792759885 51
1792759890 51
1792759895 53
1792759900 53
1792759905 53
1792759910 55
1792759915 55
1792759920 55
1792759925 55
1792759930 55
1792759935 55
1792759940 55
1792759945 55
1792759950 55
1792759955 55
1792759960 55
1792759965 55
1792759970 55
```
</details>

---

