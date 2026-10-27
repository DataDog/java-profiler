---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 19:06:19 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 172 |
| Sample Rate | 2.87/sec |
| Health Score | 179% |
| Threads | 8 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 15 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1793142128 64
1793142133 64
1793142138 64
1793142143 64
1793142148 64
1793142153 64
1793142158 64
1793142163 64
1793142168 64
1793142173 64
1793142178 64
1793142183 64
1793142188 64
1793142193 64
1793142198 64
1793142203 64
1793142208 64
1793142213 64
1793142218 64
1793142223 64
```
</details>

---

