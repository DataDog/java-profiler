---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 08:31:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 11 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (3 unique values: 40-72 cores)</summary>

```
1786364669 70
1786364674 70
1786364679 70
1786364684 70
1786364689 70
1786364694 70
1786364699 70
1786364704 70
1786364709 70
1786364714 70
1786364719 70
1786364724 72
1786364729 72
1786364734 72
1786364739 72
1786364744 72
1786364749 72
1786364754 72
1786364759 72
1786364764 72
```
</details>

---

