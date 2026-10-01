---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-01 11:00:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 13 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 43-47 cores)</summary>

```
1790866596 45
1790866601 45
1790866606 45
1790866611 45
1790866616 45
1790866621 45
1790866626 47
1790866631 47
1790866636 47
1790866641 47
1790866646 47
1790866651 47
1790866656 45
1790866661 45
1790866666 45
1790866671 45
1790866676 43
1790866681 43
1790866686 43
1790866691 43
```
</details>

---

