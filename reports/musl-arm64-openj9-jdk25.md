---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-13 05:53:08 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 12 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (3 unique values: 17-27 cores)</summary>

```
1791884916 17
1791884921 17
1791884926 17
1791884931 17
1791884936 17
1791884941 17
1791884946 27
1791884951 27
1791884956 27
1791884961 27
1791884966 27
1791884971 27
1791884976 17
1791884981 17
1791884986 22
1791884991 22
1791884996 22
1791885001 22
1791885006 22
1791885011 22
```
</details>

---

