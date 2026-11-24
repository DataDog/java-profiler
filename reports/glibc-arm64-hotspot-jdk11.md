---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 05:51:07 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 10 |
| Allocations | 188 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 33-40 cores)</summary>

```
1795517158 40
1795517163 40
1795517168 35
1795517173 35
1795517178 35
1795517183 35
1795517188 35
1795517193 35
1795517198 35
1795517203 35
1795517208 35
1795517213 33
1795517218 33
1795517223 33
1795517228 33
1795517233 33
1795517238 33
1795517243 33
1795517248 33
1795517253 33
```
</details>

---

