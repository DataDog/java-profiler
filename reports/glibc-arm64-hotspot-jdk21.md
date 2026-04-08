---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-08 09:54:16 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 14 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1775656139 64
1775656144 64
1775656149 64
1775656154 64
1775656159 64
1775656164 64
1775656169 64
1775656174 64
1775656179 64
1775656184 64
1775656189 64
1775656194 64
1775656199 64
1775656204 64
1775656209 64
1775656214 64
1775656219 64
1775656224 64
1775656229 64
1775656234 64
```
</details>

---

