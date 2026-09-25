---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-25 06:35:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 7 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 223 |
| Sample Rate | 3.72/sec |
| Health Score | 233% |
| Threads | 11 |
| Allocations | 157 |

<details>
<summary>CPU Timeline (3 unique values: 46-64 cores)</summary>

```
1790332194 46
1790332199 46
1790332204 46
1790332209 46
1790332214 46
1790332219 46
1790332224 46
1790332229 46
1790332234 46
1790332239 46
1790332244 46
1790332249 46
1790332254 46
1790332259 46
1790332264 64
1790332269 64
1790332274 64
1790332279 64
1790332284 64
1790332289 64
```
</details>

---

