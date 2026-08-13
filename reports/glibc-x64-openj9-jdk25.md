---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-13 03:49:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (5 unique values: 28-57 cores)</summary>

```
1786607128 28
1786607133 28
1786607138 28
1786607143 28
1786607148 39
1786607153 39
1786607158 31
1786607163 31
1786607168 31
1786607173 31
1786607178 31
1786607183 31
1786607188 57
1786607193 57
1786607198 57
1786607203 57
1786607208 57
1786607213 57
1786607218 57
1786607223 57
```
</details>

---

