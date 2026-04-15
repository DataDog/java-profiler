---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-15 13:26:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 12 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776273638 64
1776273643 64
1776273648 64
1776273653 64
1776273658 64
1776273663 64
1776273668 64
1776273673 64
1776273678 64
1776273683 64
1776273688 64
1776273693 64
1776273698 64
1776273703 64
1776273708 64
1776273713 64
1776273718 64
1776273723 64
1776273728 64
1776273733 64
```
</details>

---

