---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 12:27:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 208 |
| Sample Rate | 3.47/sec |
| Health Score | 217% |
| Threads | 11 |
| Allocations | 98 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794504141 48
1794504146 48
1794504151 48
1794504156 48
1794504161 48
1794504166 48
1794504171 48
1794504176 48
1794504181 48
1794504186 48
1794504191 48
1794504196 48
1794504202 48
1794504207 48
1794504212 48
1794504217 48
1794504222 48
1794504227 48
1794504232 48
1794504237 43
```
</details>

---

