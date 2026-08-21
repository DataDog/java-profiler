---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-21 11:01:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 12 |
| Allocations | 144 |

<details>
<summary>CPU Timeline (5 unique values: 42-48 cores)</summary>

```
1787324196 48
1787324201 48
1787324206 48
1787324211 47
1787324216 47
1787324221 42
1787324226 42
1787324231 42
1787324236 42
1787324241 43
1787324246 43
1787324251 43
1787324256 43
1787324261 43
1787324266 43
1787324271 48
1787324276 48
1787324281 48
1787324286 48
1787324291 48
```
</details>

---

