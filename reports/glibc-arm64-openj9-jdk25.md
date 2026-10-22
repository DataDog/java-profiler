---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 18:25:49 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 12 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792707699 43
1792707704 43
1792707709 43
1792707714 43
1792707719 43
1792707724 43
1792707729 43
1792707734 48
1792707739 48
1792707744 48
1792707749 48
1792707754 48
1792707759 48
1792707764 48
1792707769 48
1792707774 48
1792707779 48
1792707784 48
1792707789 48
1792707794 48
```
</details>

---

