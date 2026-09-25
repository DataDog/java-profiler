---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-25 06:35:12 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790332168 50
1790332173 50
1790332178 50
1790332183 50
1790332188 50
1790332193 50
1790332198 50
1790332203 50
1790332208 50
1790332213 50
1790332218 50
1790332223 50
1790332228 50
1790332233 50
1790332238 50
1790332243 50
1790332248 50
1790332253 50
1790332258 50
1790332263 50
```
</details>

---

