---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 00:59:15 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 34-64 cores)</summary>

```
1790225658 64
1790225663 64
1790225668 64
1790225673 64
1790225678 64
1790225683 64
1790225688 64
1790225693 64
1790225698 64
1790225703 64
1790225708 64
1790225713 64
1790225718 34
1790225723 34
1790225728 34
1790225733 34
1790225738 34
1790225743 34
1790225748 34
1790225753 34
```
</details>

---

