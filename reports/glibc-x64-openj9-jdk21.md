---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-06 06:41:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 10 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (2 unique values: 22-24 cores)</summary>

```
1791282923 22
1791282928 22
1791282933 22
1791282938 22
1791282943 22
1791282948 24
1791282953 24
1791282958 24
1791282963 24
1791282968 24
1791282973 24
1791282978 24
1791282983 24
1791282988 24
1791282993 24
1791282998 24
1791283003 24
1791283008 24
1791283013 24
1791283018 24
```
</details>

---

