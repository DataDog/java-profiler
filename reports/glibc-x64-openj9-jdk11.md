---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:08:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 143 |
| Sample Rate | 2.38/sec |
| Health Score | 149% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 9 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (5 unique values: 72-93 cores)</summary>

```
1794506556 72
1794506561 72
1794506566 74
1794506571 74
1794506576 74
1794506581 74
1794506586 74
1794506591 74
1794506596 91
1794506601 91
1794506606 91
1794506611 91
1794506616 91
1794506621 93
1794506626 93
1794506631 88
1794506636 88
1794506641 88
1794506646 88
1794506651 88
```
</details>

---

