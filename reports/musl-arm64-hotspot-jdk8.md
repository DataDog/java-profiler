---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-23 21:24:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 21-26 cores)</summary>

```
1787534392 21
1787534397 21
1787534402 26
1787534407 26
1787534412 26
1787534417 26
1787534422 26
1787534427 26
1787534432 26
1787534437 26
1787534442 26
1787534447 26
1787534452 26
1787534457 26
1787534462 26
1787534467 26
1787534472 26
1787534477 26
1787534482 26
1787534487 26
```
</details>

---

