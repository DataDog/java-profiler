---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-10 11:02:58 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 9 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 24-28 cores)</summary>

```
1775833146 24
1775833151 24
1775833156 24
1775833161 24
1775833166 26
1775833171 26
1775833176 26
1775833181 26
1775833186 26
1775833191 26
1775833196 26
1775833201 26
1775833206 26
1775833211 26
1775833216 26
1775833221 26
1775833226 26
1775833231 26
1775833236 28
1775833241 28
```
</details>

---

