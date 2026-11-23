---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 07:20:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (6 unique values: 39-48 cores)</summary>

```
1795436143 41
1795436148 41
1795436153 41
1795436158 39
1795436163 39
1795436168 44
1795436173 44
1795436178 44
1795436183 44
1795436188 44
1795436193 44
1795436198 44
1795436203 44
1795436208 44
1795436213 44
1795436218 44
1795436223 46
1795436228 46
1795436233 48
1795436238 48
```
</details>

---

