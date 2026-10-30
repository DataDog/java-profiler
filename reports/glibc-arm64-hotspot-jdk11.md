---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 10:36:03 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 208 |
| Sample Rate | 3.47/sec |
| Health Score | 217% |
| Threads | 12 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793370699 48
1793370704 48
1793370709 48
1793370714 48
1793370719 48
1793370724 48
1793370729 48
1793370734 48
1793370739 48
1793370744 48
1793370749 48
1793370754 48
1793370759 48
1793370764 48
1793370769 48
1793370774 48
1793370779 48
1793370784 48
1793370789 48
1793370794 48
```
</details>

---

