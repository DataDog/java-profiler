---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-21 10:48:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 159 |
| Sample Rate | 2.65/sec |
| Health Score | 166% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 13 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (3 unique values: 51-64 cores)</summary>

```
1792593777 51
1792593782 51
1792593787 51
1792593792 51
1792593797 51
1792593802 51
1792593807 51
1792593812 51
1792593817 51
1792593822 51
1792593827 51
1792593833 51
1792593838 51
1792593843 51
1792593848 64
1792593853 64
1792593858 64
1792593863 64
1792593868 64
1792593873 64
```
</details>

---

