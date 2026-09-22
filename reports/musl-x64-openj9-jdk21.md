---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 09:50:46 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (4 unique values: 82-86 cores)</summary>

```
1790084736 85
1790084741 85
1790084746 85
1790084751 85
1790084756 85
1790084761 84
1790084766 84
1790084771 84
1790084776 84
1790084781 84
1790084786 84
1790084791 84
1790084796 84
1790084801 84
1790084806 86
1790084811 86
1790084817 84
1790084822 84
1790084827 82
1790084832 82
```
</details>

---

