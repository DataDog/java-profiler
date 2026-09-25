---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-25 06:35:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 9 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790332171 48
1790332176 48
1790332181 48
1790332186 48
1790332191 48
1790332196 48
1790332201 48
1790332206 48
1790332211 48
1790332216 48
1790332221 48
1790332226 48
1790332231 48
1790332236 48
1790332241 48
1790332246 43
1790332251 43
1790332256 43
1790332261 43
1790332266 43
```
</details>

---

