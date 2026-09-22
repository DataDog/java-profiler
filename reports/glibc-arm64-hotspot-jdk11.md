---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 13:10:29 EDT

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
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 87 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790096731 48
1790096736 48
1790096741 48
1790096746 48
1790096751 48
1790096756 48
1790096761 48
1790096766 48
1790096771 48
1790096776 48
1790096781 48
1790096786 48
1790096791 48
1790096796 48
1790096801 48
1790096806 43
1790096811 43
1790096816 43
1790096821 43
1790096826 43
```
</details>

---

