---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-29 07:13:54 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 9 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1790680186 48
1790680191 48
1790680196 48
1790680201 48
1790680206 48
1790680211 48
1790680216 48
1790680221 48
1790680226 48
1790680231 48
1790680236 46
1790680241 46
1790680246 46
1790680251 46
1790680256 46
1790680261 46
1790680266 46
1790680271 46
1790680276 48
1790680281 48
```
</details>

---

