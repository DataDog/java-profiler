---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 11:53:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 11 |
| Allocations | 107 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793288659 48
1793288664 48
1793288669 48
1793288674 48
1793288679 48
1793288684 48
1793288689 48
1793288694 48
1793288699 48
1793288704 48
1793288709 48
1793288714 48
1793288719 48
1793288724 48
1793288729 48
1793288734 48
1793288739 48
1793288744 48
1793288749 48
1793288754 48
```
</details>

---

