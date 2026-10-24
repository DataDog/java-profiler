---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-24 05:55:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 154 |
| Sample Rate | 2.57/sec |
| Health Score | 161% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 62-96 cores)</summary>

```
1792835526 63
1792835531 63
1792835536 63
1792835541 63
1792835546 63
1792835551 63
1792835556 63
1792835561 63
1792835566 96
1792835571 96
1792835576 96
1792835581 96
1792835586 62
1792835591 62
1792835596 62
1792835601 62
1792835606 62
1792835611 62
1792835616 62
1792835621 62
```
</details>

---

