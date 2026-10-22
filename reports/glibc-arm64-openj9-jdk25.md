---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 13:25:21 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (3 unique values: 49-64 cores)</summary>

```
1792689639 49
1792689644 49
1792689649 49
1792689654 49
1792689659 49
1792689664 49
1792689669 49
1792689674 49
1792689679 49
1792689684 49
1792689689 49
1792689694 49
1792689699 49
1792689704 54
1792689709 54
1792689714 54
1792689719 54
1792689724 54
1792689729 54
1792689734 54
```
</details>

---

