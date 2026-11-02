---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 11:54:31 EST

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 8 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 252 |
| Sample Rate | 4.20/sec |
| Health Score | 262% |
| Threads | 13 |
| Allocations | 158 |

<details>
<summary>CPU Timeline (2 unique values: 9-14 cores)</summary>

```
1793638152 14
1793638157 14
1793638162 14
1793638167 14
1793638172 14
1793638177 14
1793638182 14
1793638187 14
1793638192 14
1793638197 9
1793638202 9
1793638207 9
1793638213 9
1793638218 9
1793638223 9
1793638228 9
1793638233 9
1793638238 9
1793638243 9
1793638248 14
```
</details>

---

