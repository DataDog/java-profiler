---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 11:01:37 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 10 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 14-17 cores)</summary>

```
1793112855 16
1793112860 16
1793112865 16
1793112870 16
1793112875 16
1793112880 16
1793112885 16
1793112890 16
1793112895 16
1793112900 16
1793112905 16
1793112910 16
1793112915 14
1793112920 14
1793112925 14
1793112930 14
1793112935 14
1793112940 14
1793112945 14
1793112950 14
```
</details>

---

