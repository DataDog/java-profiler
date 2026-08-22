---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-22 11:45:52 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 58-66 cores)</summary>

```
1787413237 66
1787413242 66
1787413247 66
1787413252 66
1787413257 66
1787413262 66
1787413267 58
1787413272 58
1787413277 58
1787413282 58
1787413287 58
1787413292 58
1787413297 58
1787413302 58
1787413307 58
1787413312 58
1787413317 58
1787413322 58
1787413327 58
1787413332 58
```
</details>

---

