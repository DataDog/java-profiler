---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 12:28:34 EDT

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 8 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (5 unique values: 29-34 cores)</summary>

```
1790094099 33
1790094104 33
1790094109 33
1790094114 33
1790094119 33
1790094124 34
1790094129 34
1790094134 31
1790094139 31
1790094144 31
1790094149 31
1790094154 31
1790094159 31
1790094164 31
1790094169 31
1790094174 31
1790094179 31
1790094184 29
1790094189 29
1790094194 30
```
</details>

---

