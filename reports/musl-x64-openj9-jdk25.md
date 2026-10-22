---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 18:25:52 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 21-23 cores)</summary>

```
1792707659 23
1792707664 23
1792707669 23
1792707674 23
1792707679 23
1792707684 23
1792707689 23
1792707694 21
1792707699 21
1792707704 21
1792707709 21
1792707714 21
1792707719 21
1792707724 21
1792707729 21
1792707734 21
1792707739 21
1792707744 21
1792707749 21
1792707754 21
```
</details>

---

