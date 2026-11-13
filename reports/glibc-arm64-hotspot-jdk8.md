---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-13 07:26:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1794572484 48
1794572489 48
1794572494 48
1794572499 48
1794572504 48
1794572509 48
1794572514 48
1794572519 48
1794572524 48
1794572529 48
1794572534 48
1794572539 43
1794572544 43
1794572549 43
1794572554 43
1794572559 43
1794572564 43
1794572569 43
1794572574 43
1794572579 43
```
</details>

---

