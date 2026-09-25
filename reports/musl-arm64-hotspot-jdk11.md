---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-25 00:58:49 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 15 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (3 unique values: 22-27 cores)</summary>

```
1790312106 22
1790312111 22
1790312116 22
1790312121 22
1790312126 22
1790312131 27
1790312136 27
1790312141 27
1790312146 27
1790312151 27
1790312156 27
1790312161 27
1790312166 27
1790312171 27
1790312176 27
1790312181 25
1790312186 25
1790312191 25
1790312196 25
1790312201 25
```
</details>

---

