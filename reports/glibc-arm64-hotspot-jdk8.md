---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-22 13:10:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 44-50 cores)</summary>

```
1790096746 44
1790096751 44
1790096756 44
1790096761 44
1790096766 44
1790096771 49
1790096776 49
1790096781 49
1790096786 49
1790096791 49
1790096796 49
1790096801 49
1790096806 49
1790096811 49
1790096816 49
1790096821 49
1790096826 50
1790096831 50
1790096836 50
1790096841 50
```
</details>

---

