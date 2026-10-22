---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 08:00:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 87 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (3 unique values: 39-48 cores)</summary>

```
1792670106 39
1792670111 39
1792670116 39
1792670121 39
1792670126 39
1792670131 39
1792670136 46
1792670141 46
1792670146 46
1792670151 46
1792670156 46
1792670161 46
1792670166 46
1792670171 46
1792670176 46
1792670181 46
1792670186 46
1792670191 48
1792670196 48
1792670201 48
```
</details>

---

