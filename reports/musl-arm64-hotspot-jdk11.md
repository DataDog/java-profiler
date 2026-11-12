---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 12:27:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 12 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794504096 48
1794504101 48
1794504106 48
1794504111 48
1794504116 43
1794504121 43
1794504126 43
1794504131 43
1794504136 43
1794504141 43
1794504146 43
1794504151 43
1794504156 43
1794504161 43
1794504166 43
1794504171 43
1794504176 43
1794504181 43
1794504186 48
1794504191 48
```
</details>

---

