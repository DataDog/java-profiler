---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 07:03:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (3 unique values: 45-48 cores)</summary>

```
1790161159 46
1790161164 48
1790161169 48
1790161174 48
1790161179 48
1790161184 45
1790161189 45
1790161194 45
1790161199 45
1790161205 45
1790161210 45
1790161215 45
1790161220 45
1790161225 45
1790161230 45
1790161235 45
1790161240 45
1790161245 45
1790161250 45
1790161255 45
```
</details>

---

