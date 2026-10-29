---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-29 11:55:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 11 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1793288984 64
1793288989 64
1793288994 64
1793288999 64
1793289004 64
1793289009 66
1793289014 66
1793289019 66
1793289024 66
1793289029 66
1793289034 66
1793289039 66
1793289044 66
1793289049 66
1793289054 66
1793289059 66
1793289064 66
1793289069 66
1793289074 66
1793289079 66
```
</details>

---

