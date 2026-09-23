---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-23 05:40:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 10 |
| Allocations | 179 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 795 |
| Sample Rate | 13.25/sec |
| Health Score | 828% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790156122 43
1790156127 43
1790156132 43
1790156137 43
1790156142 43
1790156147 43
1790156152 43
1790156157 43
1790156162 43
1790156167 43
1790156172 43
1790156177 48
1790156182 48
1790156187 48
1790156192 48
1790156197 48
1790156202 48
1790156207 48
1790156212 48
1790156217 48
```
</details>

---

