---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 11:01:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 321 |
| Sample Rate | 5.35/sec |
| Health Score | 334% |
| Threads | 12 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793112926 32
1793112931 32
1793112936 32
1793112941 32
1793112946 32
1793112951 32
1793112956 32
1793112961 32
1793112966 32
1793112971 32
1793112976 32
1793112981 32
1793112986 32
1793112991 32
1793112996 32
1793113001 32
1793113006 32
1793113011 32
1793113016 32
1793113021 32
```
</details>

---

