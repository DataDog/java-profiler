---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 12:28:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 66-86 cores)</summary>

```
1790094064 76
1790094069 76
1790094074 76
1790094079 66
1790094084 66
1790094089 66
1790094094 66
1790094099 66
1790094104 66
1790094109 66
1790094114 66
1790094119 66
1790094124 66
1790094129 76
1790094134 76
1790094139 76
1790094144 76
1790094149 76
1790094154 86
1790094159 86
```
</details>

---

