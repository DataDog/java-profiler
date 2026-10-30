---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 06:16:25 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 14 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793355174 43
1793355179 43
1793355184 43
1793355189 43
1793355194 43
1793355199 43
1793355204 43
1793355209 43
1793355214 43
1793355219 43
1793355224 43
1793355229 43
1793355234 43
1793355239 43
1793355244 43
1793355249 43
1793355254 43
1793355259 43
1793355264 43
1793355269 43
```
</details>

---

