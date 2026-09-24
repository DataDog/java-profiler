---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 05:34:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 23-63 cores)</summary>

```
1790242171 27
1790242176 27
1790242181 27
1790242186 27
1790242191 27
1790242196 27
1790242201 27
1790242206 27
1790242211 27
1790242216 27
1790242221 27
1790242226 27
1790242231 27
1790242236 27
1790242241 63
1790242246 63
1790242251 23
1790242256 23
1790242261 23
1790242266 23
```
</details>

---

