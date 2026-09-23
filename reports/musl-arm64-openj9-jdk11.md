---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 07:03:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 9 |
| Allocations | 201 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 6 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790161159 50
1790161164 50
1790161169 50
1790161174 50
1790161179 50
1790161184 50
1790161189 50
1790161194 50
1790161199 50
1790161204 50
1790161209 50
1790161214 50
1790161219 50
1790161224 50
1790161229 50
1790161234 50
1790161239 50
1790161244 50
1790161249 50
1790161254 50
```
</details>

---

